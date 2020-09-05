;; Pingus - A free Lemmings clone
;; Copyright (C) 2019 Ingo Ruhnke <grumbel@gmail.com>
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

(set! %load-path
  (cons* "/ipfs/QmdHSWX34MXZeAgMuDuFwrYzSPf4fknX7E7cYJ7HDxaLrZ/guix-cocfree_0.0.0-62-g3b27118"
         %load-path))

(use-modules (guix build-system cmake)
             ((guix licenses) #:prefix license:)
             (guix packages)
             (gnu packages audio)
             (gnu packages freedesktop)
             (gnu packages gcc)
             (gnu packages gl)
             (gnu packages glib)
             (gnu packages image)
             (gnu packages pkg-config)
             (gnu packages pretty-print)
             (gnu packages sdl)
             (gnu packages serialization)
             (guix-cocfree utils))

(define %source-dir (dirname (current-filename)))

(define-public pingus
  (package
   (name "pingus")
   (version (version-from-source %source-dir))
   (source (source-from-source %source-dir #:version version))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #f)) ; network access needed for URL checks
   (native-inputs
    `(("pkg-config" ,pkg-config)
      ("desktop-file-utils" ,desktop-file-utils)
      ("appstream-glib" ,appstream-glib)
      ("gcc-10" ,gcc-10))) ; needed for <filesystem>
   (inputs
    `(("sdl2" ,sdl2)
      ("sdl2-image" ,sdl2-image)
      ("sdl2-mixer" ,sdl2-mixer)
      ("mesa" ,mesa)
      ("glu" ,glu)
      ("libpng" ,libpng)
      ("libsigc++" ,libsigc++)
      ("fmt" ,fmt)
      ("jsoncpp" ,jsoncpp)))
   (synopsis (synopsis-from-source %source-dir))
   (description (description-from-source %source-dir))
   (home-page (homepage-from-source %source-dir))
   (license license:gpl3+)))

pingus

;; EOF ;;