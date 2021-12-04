diagnostic_report = []
with open('input3.txt', 'r') as f:
    for line in f:
        current_entry = line.strip().split(' ') # 111100101100
        diagnostic_report.append(current_entry)
    
print(diagnostic_report)
print(len(diagnostic_report))