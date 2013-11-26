(
    (define (pow n p)
        (if (= p 0)
            1
            (* n (pow n (- p 1)))
            )
        )
        
    (define (fact n)
        (if (= n 1)
            1
            (* n (fact (- n 1)))
            )
        )
        
    (define (sum2 n) 
        (if (= n 1) 
            1
            (+ n (sum2 (- n 1)))
            )
        )
        
    (define (sum2smart n) (/ (*  n (+ n 1)) 2))
    
    (display (sum2 1000))
)