import pandas as pd
import matplotlib.pyplot as plt

# Load the Excel file

df = pd.read_excel(r'C:\Users\preto\Desktop\ac energy meter data.xlsx')

# Convert columns to numeric, forcing errors to NaN, then drop NaN rows
df['input pk'] = pd.to_numeric(df['input pk'], errors='coerce')
df['voltmeter i/p'] = pd.to_numeric(df['voltmeter i/p'], errors='coerce')
df['volt o/p'] = pd.to_numeric(df['volt o/p'], errors='coerce')
df['current i/p'] = pd.to_numeric(df['current i/p'], errors='coerce')
df['current o/p'] = pd.to_numeric(df['current o/p'], errors='coerce')

# Drop rows with missing values
df.dropna(subset=['input pk', 'voltmeter i/p', 'volt o/p', 'current i/p', 'current o/p'], inplace=True)

# Create the first plot (Voltmeter Input and Output)
plt.figure(figsize=(12, 6))

# Plot voltmeter i/p
plt.subplot(2, 1, 1)  # Create a subplot for voltage
plt.plot(df['input pk'], df['voltmeter i/p'], label='Voltmeter Input', marker='o')
plt.plot(df['input pk'], df['volt o/p'], label='Volt Output', marker='s')

# Add labels and title
plt.xlabel('Input pk')
plt.ylabel('Voltage (V)')
plt.title('Voltmeter Input and Output vs Input pk')
plt.legend()
plt.grid(True)

# Create the second plot (Current Input and Output)
plt.subplot(2, 1, 2)  # Create another subplot for current
plt.plot(df['input pk'], df['current i/p'], label='Current Input', marker='o', color='orange')
plt.plot(df['input pk'], df['current o/p'], label='Current Output', marker='s', color='green')

# Add labels and title
plt.xlabel('Input pk')
plt.ylabel('Current (A)')
plt.title('Current Input and Output vs Input pk')
plt.legend()
plt.grid(True)

# Adjust the layout so plots don't overlap
plt.tight_layout()

# Display the plot
plt.show()
