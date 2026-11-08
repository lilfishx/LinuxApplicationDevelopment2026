Name:           guess
Version:        1.0.0
Release:        alt1
Summary:        A utility for guesing picked numbers
Group:          Other
License:        MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/08_Packaging
Source:         %name-%version.tar.gz

Packager: Repository Clone <clone@altlinux.org>

BuildRequires:  make
BuildRequires:  gcc
BuildRequires:  gettext-devel

%description
This is a standard Unix command line internationalized game where the 
computer attempts to deduce the number you have picked.

%prep
%setup -q

%build
%configure
%make_build

%install
mkdir -p %buildroot

make install DESTDIR=%buildroot

%find_lang %{name}

%files -f %{name}.lang
%{_bindir}/guess

%changelog
* Sun Nov 1 2026 Repository Clone <clone@altlinux.org> 1.0.0-alt1
- Initial build