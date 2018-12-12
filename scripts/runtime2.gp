set title "svpwm"
set xlabel "time"
set ylabel "Voltage"
set terminal png font " Times_New_Roman,12 "
set output "statistic1.png"

set key right 

plot [:401][:]\
"123.txt" using 1:2 with linespoints linewidth 2 title "X", \
"123.txt" using 1:3 with linespoints linewidth 2 title "Y", \
"123.txt" using 1:4 with linespoints linewidth 2 title "Z", \


