;;;;;;;;;;;;;;
; Homework 2 ;
;;;;;;;;;;;;;;

;;;;;;;;;;;;;;
; Question 1 ;
;;;;;;;;;;;;;;

; BFS takes in a list of search trees and returns a list of nodes
; as visited through breadth first search from left to right
; examples:
; > (BFS '((((L E) F) T)))
; (T F L E)
; > (BFS '(((A (B)) C (D))))
; (C A D B)

(defun BFS (FRINGE)
	(cond
		; if fringe is null, return empty list
		((null FRINGE) '())
		; if fringe is just an atomic element, return as is
		((atom FRINGE) FRINGE)
		; if the first element is an atom, return it applying
		; bfs to the remainder of fringe
		((atom (car FRINGE)) (cons (car FRINGE) (BFS (cdr FRINGE))))
		; else, the first element is a tree. So we reorder to process
		; the remainder of fringe first, then process the tree
		(t (BFS (append (cdr FRINGE) (car FRINGE))))
	)
)

;;;;;;;;;;;;;;
; Question 2 ;
;;;;;;;;;;;;;;


; These functions implement a depth-first solver for the homer-baby-dog-poison
; problem. In this implementation, a state is represented by a single list
; (homer baby dog poison), where each variable is T if the respective entity is
; on the west side of the river, and NIL if it is on the east side.
; Thus, the initial state for this problem is (NIL NIL NIL NIL) (everybody 
; is on the east side) and the goal state is (T T T T).

; The main entry point for this solver is the function DFS, which is called
; with (a) the state to search from and (b) the path to this state. It returns
; the complete path from the initial state to the goal state: this path is a
; list of intermediate problem states. The first element of the path is the
; initial state and the last element is the goal state. Each intermediate state
; is the state that results from applying the appropriate operator to the
; preceding state. If there is no solution, DFS returns NIL.
; To call DFS to solve the original problem, one would call 
; (DFS '(NIL NIL NIL NIL) NIL) 
; However, it should be possible to call DFS with a different initial
; state or with an initial path.

; First, we define the helper functions of DFS.

; FINAL-STATE takes a single argument S, the current state, and returns T if it
; is the goal state (T T T T) and NIL otherwise.
(defun FINAL-STATE (S)
	; use equal function to compare S and with final state
	(equal '(T T T T) S)
)

; NEXT-STATE returns the state that results from applying an operator to the
; current state. It takes two arguments: the current state (S), and which entity
; to move (A, equal to h for homer only, b for homer with baby, d for homer 
; with dog, and p for homer with poison). 
; It returns a list containing the state that results from that move.
; If applying this operator results in an invalid state (because the dog and baby,
; or poison and baby are left unsupervised on one side of the river), or when the
; action is impossible (homer is not on the same side as the entity) it returns NIL.
; NOTE that next-state returns a list containing the successor state (which is
; itself a list); the return should look something like ((NIL NIL T T)).
(defun NEXT-STATE (S A)
	; first label elements of S for ease of access
	(let
		(
			(homer (first S))
		 	(baby (second S))
		 	(dog (third S))
		 	(poison (fourth S))
		)

		(cond
			; case we move homer
			((equal 'h A)
			 	(cond
			 		; ensure baby won't be left along with dog or poison if homer leaves
			    	((and (or (equal baby poison) (equal dog baby)) (equal homer baby)) NIL)
			    	; otherwise we're fine so return state with homer position switched
			    	(t (list (cons (not homer) (cdr S))))
			 	)
			)
			; case we move homer with the baby
			((equal 'b A)
				(cond
					; ensure homer and baby on same side
					((not (equal homer baby)) NIL)
					; return state with baby and homer switched
					(t (list (list (not homer) (not baby) dog poison)))
				)
			)
			; case we move homer with the dog
			((equal 'd A)
				(cond
					; ensure homer and dog on same side
					; and that baby won't be left alone with poison
					((or (not (equal homer dog)) (equal baby poison)) NIL)
					; return state with homer and dog switched
					(t (list (list (not homer) baby (not dog) poison)))
				)
			)
			; case we move homer with the poison
			((equal 'p A)
				(cond
					; ensure homer and poison on same side
					; and that baby won't be left alone with dog
					((or (not (equal homer poison)) (equal baby dog)) NIL)
					; return state with poison and homer switched
					(t (list (list (not homer) baby dog (not poison))))
				)
			)
			(t NIL)
		)
	)
)

; SUCC-FN returns all of the possible legal successor states to the current
; state. It takes a single argument (s), which encodes the current state, and
; returns a list of each state that can be reached by applying legal operators
; to the current state.
(defun SUCC-FN (S)
	; simply call NEXT-STATE on S with each possible move
	(append 
		(NEXT-STATE S 'h)
		(NEXT-STATE S 'b)
		(NEXT-STATE S 'd)
		(NEXT-STATE S 'p)
	)
)

; ON-PATH checks whether the current state is on the stack of states visited by
; this depth-first search. It takes two arguments: the current state (S) and the
; stack of states visited by DFS (STATES). It returns T if s is a member of
; states and NIL otherwise.
(defun ON-PATH (S STATES)
	(cond 
		; if there are no more states left to compare, return NIL
		((null STATES) NIL)
		; if first state matches S, return T
		((equal (car STATES) S) T)
		; check recursively if S is equal to any remaining states
		(t (ON-PATH S (cdr STATES)))
	)
)

; MULT-DFS is a helper function for DFS. It takes two arguments: a list of
; states from the initial state to the current state (PATH), and the legal
; successor states to the last, current state in the PATH (STATES). PATH is a
; first-in first-out list of states; that is, the first element is the initial
; state for the current search and the last element is the most recent state
; explored. MULT-DFS does a depth-first search on each element of STATES in
; turn. If any of those searches reaches the final state, MULT-DFS returns the
; complete path from the initial state to the goal state. Otherwise, it returns
; NIL.
(defun MULT-DFS (STATES PATH)
	(cond
		; if we run out of states return NIL
		((null STATES) NIL)
		; if DFS on current state returns NIL, call MULT-DFS on remaining states
		((null (DFS (car STATES) PATH)) (MULT-DFS (cdr STATES) PATH))
		; otherwise we found final state so return the path using DFS
		(t (DFS (car STATES) PATH))
	)
)

; DFS does a depth first search from a given state to the goal state. It
; takes two arguments: a state (S) and the path from the initial state to S
; (PATH). If S is the initial state in our search, PATH is set to NIL. DFS
; performs a depth-first search starting at the given state. It returns the path
; from the initial state to the goal state, if any, or NIL otherwise. DFS is
; responsible for checking if S is already the goal state, as well as for
; ensuring that the depth-first search does not revisit a node already on the
; search path.
(defun DFS (S PATH)
	(cond
		; if current state already on path, return NIL
		((ON-PATH S PATH) NIL)
		; if reached final state, then return path with state appended
		((FINAL-STATE S) (append PATH (list S)))
		; otherwise call MULT-DFS on all possible successor states
		(t (MULT-DFS (SUCC-FN S) (append PATH (list S))))
	)
)
