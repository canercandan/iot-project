;; ------------------------------------------------
;; add the following line to your ~/.emacs file in
;; replacing $CEG by the absolute CEG path:
;;
;; (if (file-exists-p "~/.myemacs")
;;     (load-file "$CEG/doc/emacs_macros.el"))
;; ------------------------------------------------

(fset 'ceg-add-definition
      "\
\C-a\C-k#ifndef \C-y\C-[[1;5D\C-[u_H
#define \C-y\C-[[1;5D\C-[u_H

class \C-y
{
public:
\C-y();
~\C-y();
};

#endif // !\C-y\C-[[1;5D\C-[u_H
")

(global-set-key (kbd "C-c c d") 'ceg-add-definition)

(fset 'ceg-add-implementation
      "\
\C-a\C-k#include \"\C-y.h\"

\C-y::\C-y()
{}

\C-y::~\C-y()
{}
")

(global-set-key (kbd "C-c c i") 'ceg-add-implementation)

(fset 'add-license-gplv2
      "\
// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyright (C) 2010 CEG development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: CEG <ceg@ionlythink.com>, http://www.ionlythink.com
 */

")

(global-set-key (kbd "C-c c l") 'add-license-gplv2)
