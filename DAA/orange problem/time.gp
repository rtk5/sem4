set terminal png size 800,600
set output "time_graph_PES2UG23CS485.png"
set title "Text Length vs Execution Time"
set xlabel "Text Length"
set ylabel "Time (nanoseconds)"
set key outside
set grid

# Ensure Gnuplot reads CSV format
set datafile separator ","

# Skip the header row and plot the data
plot "horspool_values.txt" using 2:4 every ::2 with linespoints pt 7 lw 2 title "Horspool", \
     "boyermoore_values.txt" using 2:4 every ::2 with linespoints pt 9 lw 2 title "Boyer-Moore"

