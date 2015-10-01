;; Turn off the stupid stuff that wastes space
(menu-bar-mode   -1);
(tool-bar-mode   -1);
(scroll-bar-mode -1);

(package-initialize)
(require 'multiple-cursors)

;; Adding support for ggtags
;; Pressing Meta-. on a symbol in your code will let you search
;; for its definition. (https://github.com/leoliu/ggtags)
(add-hook 'c-mode-common-hook
	  (lambda ()
	    (when (derived-mode-p 'c-mode 'c++-mode 'java-mode)
	      (ggtags-mode 1))))

;; Use hippie expand rather than dabbrevs dabbrevs
;; Amazing text completion service. (There are even better ones.)
(global-set-key (kbd "<backtab>") 'dabbrev-expand)

;; Fuzzy find in current git repo.
(global-set-key (kbd "C-x C-p") 'find-file-in-project)

;; Mark many lines, adds a cursor to each.
(global-set-key (kbd "C-S-M") 'mc/edit-lines)

;; Search symbols in code
(global-set-key (kbd "M-i") 'idomenu)

;; Fuzzy M-x search
(global-set-key (kbd "M-x") 'smex)

;; Highlighting symbols
(global-set-key (kbd "M-å") 'highlight-symbol-at-point)
(global-set-key (kbd "M-ä") 'highlight-symbol-next)
(global-set-key (kbd "M-ö") 'highlight-symbol-prev)
(global-set-key (kbd "M-p") 'highlight-symbol-query-replace)

;; Alternative undo command
(global-set-key (kbd "C-S-U") 'undo)

;; Remap some keys on the mac keyboard 
(define-key key-translation-map (kbd "M-8") (kbd "["))
(define-key key-translation-map (kbd "M-9") (kbd "]"))
(define-key key-translation-map (kbd "M-(") (kbd "{"))
(define-key key-translation-map (kbd "M-)") (kbd "}"))
(define-key key-translation-map (kbd "M-7") (kbd "|"))
(define-key key-translation-map (kbd "M-/") (kbd "\\"))
(define-key key-translation-map (kbd "M-2") (kbd "@"))
(define-key key-translation-map (kbd "M-4") (kbd "$"))

