import sys
import csv
import os
import glob

def split_csv(input_file, n=20):
    with open(input_file, newline='', encoding='utf-8') as f:
        reader = csv.reader(f)
        header = next(reader)
        rows = list(reader)

    part1 = rows[:n]   # primeiras 20 linhas
    part2 = rows[n:]   # restante

    base, ext = os.path.splitext(input_file)

    file_first = f"{base}_first{n}{ext}"
    file_rest = f"{base}_rest{ext}"

    with open(file_first, "w", newline='', encoding='utf-8') as f:
        writer = csv.writer(f)
        writer.writerow(header)
        writer.writerows(part1)

    with open(file_rest, "w", newline='', encoding='utf-8') as f:
        writer = csv.writer(f)
        writer.writerow(header)
        writer.writerows(part2)

    print(f"{input_file} processado:")
    print(f"  -> {file_first}")
    print(f"  -> {file_rest}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python split_csv.py arquivo.csv ou *.csv")
        sys.exit(1)

    files = []
    for arg in sys.argv[1:]:
        expanded = glob.glob(arg)
        if expanded:
            files.extend(expanded)
        else:
            files.append(arg)

    for file in files:
        if os.path.isfile(file):
            split_csv(file)
        else:
            print(f"Aviso: {file} não encontrado.")