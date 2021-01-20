# M1 20
for i in {1..5}; do ./program.out data/wuf20-78-M1/wuf20-0100.mwcnf data/wuf20-78-M-opt.dat > 20-78-M-0100_$i.csv; done;

# M1 50
for i in {1..5}; do ./program.out data/wuf50-201-M1/wuf50-0123.mwcnf data/wuf50-201-M-opt.dat > 50-201-M-0123_$i.csv; done;

# N1 20
for i in {1..5}; do ./program.out data/wuf20-78-N1/wuf20-0118.mwcnf data/wuf20-78-N-opt.dat > 20-78-N-0118_$i.csv; done;

# N1 50
for i in {1..5}; do ./program.out data/wuf50-201-N1/wuf50-0241.mwcnf data/wuf50-201-N-opt.dat > 50-201-N-0241_$i.csv; done;

# Q1 20
for i in {1..5}; do ./program.out data/wuf20-78-Q1/wuf20-0400.mwcnf data/wuf20-78-Q-opt.dat > 20-78-Q-0400_$i.csv; done;

# Q1 50
for i in {1..5}; do ./program.out data/wuf50-201-Q1/wuf50-0987.mwcnf data/wuf50-201-Q-opt.dat > 50-201-Q-0987_$i.csv; done;

# R1 20
for i in {1..5}; do ./program.out data/wuf20-78-R1/wuf20-0109.mwcnf data/wuf20-78-R-opt.dat > 20-78-R-0109_$i.csv; done;

# R1 50
for i in {1..5}; do ./program.out data/wuf50-201-R1/wuf50-0123.mwcnf data/wuf50-201-R-opt.dat > 50-201-R-0123_$i.csv; done;

# A1 20
for i in {1..5}; do ./program.out data/wuf20-88-A1/wuf20-0125-A.mwcnf data/wuf20-88-A-opt.dat > 20-88-A-0125_$i.csv; done;
