@main:
    push 144
    invoke @isqrt
    print
    push 1
    return

@isqrt: n
    push 1
    store guess
L1: load guess
    load guess
    mul
    load n
    if_cmpgt L_done
    push 1
    load guess
    add
    store guess
    goto L1
L_done: load guess
    push 1
    sub
    return
