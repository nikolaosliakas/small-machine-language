@main:
   push 10
   invoke @fib2
   print
   push 1
   return

@fib2: n
     push 1
     store fm2
     push 1
     store fm1
     push 2
     store i
L6:  load i
     load n
     if_cmpgt L27
     load fm2
     load fm1
     add
     store f
     load fm1
     store fm2
     load f
     store fm1
     push 1
     load i
     add
     store i
     goto  L6
L27: load fm1
     return
