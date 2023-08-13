import re

def parse_top_output(file_path):
    pid_user_pairs = []

    with open(file_path, 'r') as file:
        top_output = file.read()

    lines = top_output.splitlines()
    for line in lines:
        match = re.match(r'^\s*(\d+)\s+(\S+)', line)
        if match:
            pid = match.group(1)
            user = match.group(2)
            pid_user_pairs.append((pid, user))

    return pid_user_pairs

def main():
    input_file_path = 'top_output.txt'  # Replace with your input file path
    pid_user_pairs = parse_top_output(input_file_path)

    for pid, user in pid_user_pairs:
        print(f"PID: {pid}, User: {user}")

if __name__ == '__main__':
    main()
