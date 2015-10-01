(package-initialize)

;; Make sure we load packages from many sources
(setq package-archives '(("gnu"       . "http://elpa.gnu.org/packages/")
			 ("marmalade" . "http://marmalade-repo.org/packages/")
			 ("melpa"     . "http://melpa.milkbox.net/packages/")))

;; list the packages you want
(setq package-list '(smex move-text find-file-in-project multiple-cursors idomenu highlight-symbol s))
					
;; fetch the list of packages available
(unless package-archive-contents
  (package-refresh-contents))
					
;; install the missing packages
(dolist (package package-list)
  (unless (package-installed-p package)
    (package-install package)))
