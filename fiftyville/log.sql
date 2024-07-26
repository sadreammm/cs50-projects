--get description of the crime
SELECT description FROM crime_scene_reports WHERE month=7 AND day=28 AND street='Humphrey Street';

--time of crime 10:15am

--transcript from the interviews
SELECT transcript FROM interviews WHERE month=7 AND day=28;

--airport details to find the earliest flight next day out of fiftyville
SELECT * FROM airports;
SELECT * FROM flights WHERE origin_airport_id=8 AND month=7 AND day=29 ORDER BY hour;
--earliest flight id 36 at 8:20am

--passengers details on that flight
SELECT * FROM passengers WHERE flight_id=36;

--phone call to someone for less than a minute
 SELECT * FROM phone_calls WHERE day=28 AND month=7 AND duration<60;

--thief withdrew money from atm at leggett street
SELECT * FROM atm_transactions WHERE day=28 AND month=7 AND atm_location='Leggett Street' AND transaction_type='withdraw';

--find account number and person_id
SELECT * FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day=28 AND month=7 AND atm_location='Leggett Street' AND transaction_type='withdraw');


--finding license plate from bakery security logs
SELECT * FROM bakery_security_logs WHERE day=28 AND month=7 AND hour=10 AND minute between 15 and 25 AND activity='exit';

--Finding the thief from the above info(Bruce)
SELECT name FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND duration<60)
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id=36)
AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND hour=10 AND minute between 15 and 25 AND activity='exit')
AND id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day=28 AND month=7 AND atm_location='Leggett Street' AND transaction_type='withdraw'));

--Finding the city they escaped to(NYC)
SELECT * FROM flights WHERE origin_airport_id=8 AND month=7 AND day=29 ORDER BY hour;
SELECT * FROM airports WHERE id=4;

--Finding the accomplice(robin)
SELECT name FROM people WHERE phone_number =
   ...> (SELECT receiver FROM phone_calls WHERE caller=
   ...> (SELECT phone_number FROM people WHERE name='Bruce')
   ...> AND day=28 AND month=7 AND duration<60);
