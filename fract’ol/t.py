print(''.join(
    [''.join(
        [chr(round(
            36 - 2 * (
                a := 0 + 0j,
                abs([
                    a := a * a + complex(x, y)
                    if abs(a) < 2 else (
                        1.4 + 1.5j
                    ) for _ in range(100)
                ][-1])
            )[1]
        )) for x in map(
            lambda x:x / 1000,
            range(-2000, 500, 20)
        )]
    ) + '\n' for y in map(
        lambda x:x / 1000,
        range(1000, -1000, -20)
    )]
))