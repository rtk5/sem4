set terminal png size 800,600
set output "comparison_graph_PES2UG23CS485.png"
set title "Text Length vs Number of Comparisons"
set xlabel "Text Length"
set ylabel "Number of Comparisons"
set key outside
set grid
set datafile separator ","  # Ensure correct CSV parsing
plot "horspool_values.txt" using 2:3 every ::2 with linespoints pt 7 lw 2 title "Horspool", \
     "boyermoore_values.txt" using 2:3 every ::2 with linespoints pt 9 lw 2 title "Boyer-Moore"

