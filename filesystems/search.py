from pathlib import Path

inputDir = input("Input the path for the directory you wish to search \n")
searchDir = Path(inputDir)
suffix = input("Input the suffix you wish to search for (ex: .c, .cpp) \n")

visited = set()


def findFiles(path, suffix):
    # if path has been visited then skip 
    if path in visited:
        return []
    
# mark as visited
    visited.add(path)

    matchingFiles = list (path.glob(f'*{suffix}'))

    # recursivelly check subdirectories while avoiding symlinks which can cause cycles
    for subdir in path.iterdir():
        if subdir.is_dir() and not subdir.is_symlink():
            matchingFiles.extend(findFiles(subdir, suffix))

    return matchingFiles

matchingFiles = findFiles(searchDir, suffix)

print(f"Files found with suffix {suffix} :")
if matchingFiles:
    for file_path in matchingFiles:
        print(file_path)

else:
    print(f"No files found \n")