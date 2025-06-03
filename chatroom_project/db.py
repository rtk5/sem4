import sqlite3

# Connect to the database
conn = sqlite3.connect("database/chat_logs.db")
cursor = conn.cursor()

# Query all data from logs table
cursor.execute("SELECT * FROM logs")
rows = cursor.fetchall()

# Print the data
print("Username | Room | Message | Timestamp")
print("-" * 60)
for row in rows:
    print(f"{row[0]} | {row[1]} | {row[2]} | {row[3]}")

# Close connection
conn.close()
