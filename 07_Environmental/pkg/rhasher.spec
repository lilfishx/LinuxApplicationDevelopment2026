Name:           rhasher
Version:        1.0.0
Release:        alt1
Summary:        A utility for computing cryptographic hashes
Group:          Other
License:        MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/07_Packaging
Source:         %name-%version.tar.gz

Packager: Repository Clone <clone@altlinux.org>

BuildRequires:  make
BuildRequires:  gcc
BuildRequires:  librhash-devel

%description
Rhasher is a command-line tool designed to compute cryptographic hashes.

%prep
%setup -q

%build
%configure
%make_build

%install
mkdir -p %buildroot

make install DESTDIR=%buildroot

%files
%{_bindir}/rhasher

%changelog
* Sun Nov 1 2026 Repository Clone <clone@altlinux.org> 1.0.0-alt1
- Initial build