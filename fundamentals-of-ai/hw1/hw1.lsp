; Name: Dhruv Chakraborty
; UID: 204962098
; CS 161 HW 1



;;; problem 1:
; pad takes a non-negative integer value n and
; returns the nth Padovan number given by
; pad(n+1) = pad(n-1) + pad(n-2) and
; pad(0) = pad(1) = pad(2) = 1

(defun pad (n)
	(cond
		; return 1 if n = 0,1,2 
		((or (= n 0) (= n 1) (= n 2)) 1)
		; else return pad(n-2) + pad(n-3)
    	(t (+ (pad (- n 2)) (pad (- n 3))))
	)
)



;;; problem 2:
; sums takes a non-negative integer value n and
; returns the number of additions required to 
; compute pad(n) as defined above

(defun sums (n)
	(cond
		; return 0 for the base cases 
		((or (= n 0) (= n 1) (= n 2)) 0)
		; return 1 plus sum of sums required 
		; to calculate pad(n-2) and pad(n-3)
		(t (+ 1 (sums (- n 2)) (sums (- n 3))))
	)
)

; the relationship between pad and sums is 
; observed to be pad(n) = sums(n) + 1



;;; problem 3:
; anon takes a tree and returns an anonymized
; version of its structure i.e. retains the full 
; structure of the tree but makes each element ?
; example:
; > (ANON ’(((L E) F) T))
; (((? ?) ?) ?) 

(defun anon (tree)
	(cond 
		; return empty list of empty tree
		((null tree) '())
		; return ? for an atomic element
		((atom tree) '?)
		; return recursive applications of anon to the
		; first element and the remainder of the tree
		(t (cons (anon (car tree)) (anon (cdr tree))))
	)
)		