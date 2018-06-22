def foo(a, *args, **keyvalues):
    print(a)
    for arg in args:
        print(arg, end=' ')
    print('')
    for key in keyvalues:
        print(key, ':', keyvalues[key], end=', ')
    print('')

foo('xixi', 'haha', 'huhu', name='yoleimei', height='175')