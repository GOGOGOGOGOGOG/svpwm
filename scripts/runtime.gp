set title "svpwm"
set xlabel "time"
set ylabel "Voltage"
set terminal png font " Times_New_Roman,12 "
set output "statistic.png"

set key right 

plot [:401][:]\
"output.txt" using 1:2 with linespoints linewidth 2 title "U", \
"output.txt" using 1:3 with linespoints linewidth 2 title "V", \
"output.txt" using 1:4 with linespoints linewidth 2 title "W", \


