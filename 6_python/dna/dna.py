import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: \npython dna.py str_counts.csv dna_sequences.txt")
        sys.exit(1)

    str_counts_file = sys.argv[1]
    dna_sequences_file = sys.argv[2]

    database = {}
    str_sequences = []

    with open(str_counts_file) as file:
        reader = csv.DictReader(file)
        str_sequences = reader.fieldnames[1:]
        for row in reader:
            person_name = row['name']
            database[person_name] = {str_seq: int(row[str_seq]) for str_seq in str_sequences}

    with open(dna_sequences_file) as file:
        dna_sequence = file.readline().strip()

    str_counts = {str_seq: longest_match(dna_sequence, str_seq) for str_seq in str_sequences}

    match_found = False
    for person, counts in database.items():
        if counts == str_counts:
            print(person)
            match_found = True
            break

    if not match_found:
        print("No match")


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
