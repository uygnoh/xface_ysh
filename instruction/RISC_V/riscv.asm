# java -jar rv32i.jar	 

.data
DATA:
        .word   1, 2, 3, 4, 5

.text
        la      s0, DATA
        lw      t0, 2(s0)
