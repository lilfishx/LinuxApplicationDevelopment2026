Name:           move
Version:        1.0.0
Release:        alt1
Summary:        A lightweight C program to move files safely
Group:          Other
License:        MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/06_Packaging
Source:         %name-%version.tar.gz

Packager: Repository Clone <clone@altlinux.org>

%description
A lightweight C program that moves a file from one location to another.

%prep
%setup -c

%build
%make_build PREFIX=/usr LIBDIR=%_libdir

%install
%makeinstall_std PREFIX=/usr LIBDIR=%_libdir

%files
%_bindir/move
%_bindir/safemove.sh
%_libdir/protect.so
%doc README.md

%changelog
* Sun Oct 25 2026 Repository Clone <clone@altlinux.org> 1.0.0-alt1
- Initial build