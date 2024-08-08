import csv
import sys


def main():

    if(len(sys.argv) != 3):
        print("Not enough arguments")
        return

    #Read database file into a variable
    db=[]
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        for i in reader:
            db.append(i)
        db_seq = reader.fieldnames[1:]

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as f:
        dna_seq = f.read()
    #  Find longest match of each STR in DNA sequence
    l={}
    for s in db_seq:
        l[s]=longest_match(dna_seq,s)
    # Check database for matching profiles
    for person in db:
        match = True
        for s in db_seq:
            if l[s]!=int(person[s]):
                match=False
                break
        if match:
            print(person["name"])
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
