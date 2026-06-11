@main:
   push 10
   invoke @fib
   print
   push 1
   return

@fib: n
    load n
    push 1
    if_cmpgt L7
    push 1
    return
L7: load n
    push 1
    sub
    invoke @fib
    load n
    push 2
    sub
    invoke @fib
    add
    return
