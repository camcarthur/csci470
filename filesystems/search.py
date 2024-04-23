import os
import fnmatch

def find_files_with_suffix(start_directory, suffix):
    result = []
    for dirpath, dirnames, filenames in os.walk(start_directory):
        # Use glob-style pattern matching to find files with the specific suffix
        pattern = f"*{suffix}"
        
        for filename in fnmatch.filter(filenames, pattern):
            full_path = os.path.join(dirpath, filename)
            result.append(full_path)

    return result

# Example usage
start_directory = input("Enter the path of the directory you would like to start at\n")
suffix = input("Enter the suffix you want to search for (ex: .txt, .jpeg, .cpp)\n")
files = find_files_with_suffix(start_directory, suffix)

for file in files:
    print("Found:", file)
