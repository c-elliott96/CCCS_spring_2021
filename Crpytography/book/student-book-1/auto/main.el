(TeX-add-style-hook "main"
 (lambda ()
    (TeX-run-style-hooks
     "makeidx"
     "mybookpreamble"
     "group"
     "bibliography")))

