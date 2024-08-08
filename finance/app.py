import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks_rows = db.execute(
        "SELECT symbol,SUM(shares) FROM stocks_transaction WHERE userId=? GROUP BY symbol",
        user_id,
    )

    total_price = 0
    holdings = []
    for stock in stocks_rows:
        symbol = stock["symbol"]
        shares = stock["SUM(shares)"]
        if int(shares) > 0:
            stock_dict = lookup(symbol)
            if stock_dict == None:
                return apology("stock doesn't exist", 403)

            current_price = stock_dict["price"]
            total_stock_price = current_price * shares
            total_price += total_stock_price

            holdings.append(
                {
                    "symbol": symbol,
                    "shares": shares,
                    "current_price": current_price,
                    "total_stock_price": round(total_stock_price, 2),
                }
            )

    rows = db.execute("SELECT cash FROM users WHERE id=?", user_id)
    current_cash = rows[0]["cash"]

    grand_total = current_cash + total_price

    return render_template(
        "index.html",
        holdings=holdings,
        current_cash=round(current_cash, 2),
        grand_total=round(grand_total, 2),
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        stock_dict = lookup(symbol)
        if stock_dict == None:
            return apology("Stock doesn't exist", 400)

        price = stock_dict["price"]

        user_id = session["user_id"]

        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        try:
            shares = int(shares)
        except:
            return apology("must provide a valid share", 400)

        if shares <= 0:
            return apology("must buy atleast one share", 400)

        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_cash = rows[0]["cash"]
        total_cost = price * shares

        if total_cost > current_cash:
            return apology("insufficient funds", 400)

        db.execute("UPDATE users SET cash=cash-? WHERE id=?", total_cost, user_id)
        db.execute(
            "INSERT INTO stocks_transaction(symbol,price,userId,shares) VALUES(?,?,?,?)",
            symbol,
            price,
            user_id,
            shares,
        )

        return redirect("/")
    else:
        value = request.args.get("symbol", "")
        return render_template("buy.html", symbol=value)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    stocks_transactions = db.execute(
        "SELECT * FROM stocks_transaction WHERE userId = ?", user_id
    )
    return render_template("history.html", stocks=stocks_transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide a symbol", 400)
        stock_dict = lookup(symbol)
        if stock_dict == None:
            return apology("stock doesn't exist", 400)
        price = stock_dict["price"]
        symbol = stock_dict["symbol"]
        return render_template("quoted.html", price=price, symbol=symbol)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        pw = request.form.get("password")
        confirm = request.form.get("confirmation")

        if not name:
            return apology("must provide username", 400)
        if not pw:
            return apology("must provide password", 400)
        if not confirm:
            return apology("must confirm password", 400)
        if pw != confirm:
            return apology("passwords don't match", 400)

        pw = generate_password_hash(pw)

        try:
            db.execute("INSERT INTO users(username,hash) VALUES(?,?)", name, pw)
        except:
            return apology("username already exists", 400)
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        try:
            shares = int(shares)
        except:
            return apology("must provide a valid share", 400)

        if shares <= 0:
            return apology("must sell atleast one share", 400)

        rows = db.execute(
            "SELECT symbol, SUM(shares) FROM stocks_transaction WHERE userId = ? AND symbol = ? GROUP BY symbol",
            user_id,
            symbol,
        )

        if len(rows) != 1:
            return apology("you don't own the stock", 400)
        if rows[0]["SUM(shares)"] < shares:
            return apology("you don't own that many shares", 400)

        stock_dict = lookup(symbol)
        if stock_dict == None:
            return apology("stock doesn't exist", 400)
        price = stock_dict["price"]

        total = price * shares
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total, user_id)

        db.execute(
            "INSERT INTO stocks_transaction(symbol,price,userId,shares) VALUES(?,?,?,?)",
            symbol,
            price,
            user_id,
            -int(shares),
        )

        return redirect("/")
    else:
        user_id = session["user_id"]
        value = request.args.get("symbol", "")
        rows = db.execute(
            "SELECT DISTINCT symbol FROM stocks_transaction WHERE userId = ?", user_id
        )
        return render_template("sell.html", symbol=value, stocks=rows)


@app.route("/account")
@login_required
def account():
    user_id = session["user_id"]
    rows = db.execute("SELECT username,cash FROM users WHERE id=?", user_id)
    name = rows[0]["username"].title()
    cash = rows[0]["cash"]
    return render_template("account.html", name=name, cash=cash)


@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    if request.method == "POST":
        user_id = session["user_id"]
        oldPass = request.form.get("old_password")
        newPass = request.form.get("new_password")
        confirm = request.form.get("confirm")

        if not oldPass:
            return apology("must provide password", 400)
        if not newPass:
            return apology("must provide password", 400)
        if not confirm:
            return apology("must provide password", 400)
        if newPass != confirm:
            return apology("Doesn't match the new password", 400)

        rows = db.execute("SELECT hash FROM users WHERE id=?", user_id)
        if not check_password_hash(rows[0]["hash"], oldPass):
            return apology("Incorrect Password", 400)

        newPass = generate_password_hash(newPass)
        db.execute("UPDATE users SET hash=? WHERE id=?", newPass, user_id)
        return redirect("/")
    else:
        return render_template("password.html")


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    if request.method == "POST":
        user_id = session["user_id"]
        cash = request.form.get("add_cash")
        if not cash:
            return apology("must provide an amount", 400)
        try:
            cash = float(cash)
        except:
            return apology("must provide a valid amount", 400)
        if cash < 0:
            return apology("must provide a positive amount", 400)
        db.execute("UPDATE users SET cash = cash + ? WHERE id=?", cash, user_id)
        return redirect("/")
    else:
        user_id = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = rows[0]["cash"]
        return render_template("cash.html", balance=cash)
