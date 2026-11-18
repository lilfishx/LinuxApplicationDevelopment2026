Name:           maze
Version:        1.0.0
Release:        alt1
Summary:        Random maze generator
Group:          Other
License:        MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/09_PatchDiff
Source:         %name-%version.tar.gz

Packager: Repository Clone <clone@altlinux.org>

BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  patch

%description
Random maze generator. The maze is a 13x13 character grid made of 6x6 rooms (3x3 cells each) with shared walls. 

The base version always builds a 6x6 maze. Three patches add:
  * maze size from the first command-line argument;
  * passage/wall characters from the second argument;
  * PRNG seed from the first argument (for reproducible mazes).

%prep
%setup -c

%build
make all

%install
rm -rf %{buildroot}
install -d %{buildroot}%{_bindir}
install -m 0755 maze_v0 %{buildroot}%{_bindir}/maze_v0
install -m 0755 maze_v1 %{buildroot}%{_bindir}/maze_v1
install -m 0755 maze_v2 %{buildroot}%{_bindir}/maze_v2
install -m 0755 maze_v3 %{buildroot}%{_bindir}/maze_v3

%files
%{_bindir}/maze_v0
%{_bindir}/maze_v1
%{_bindir}/maze_v2
%{_bindir}/maze_v3

%changelog
* Sun Nov 1 2026 Repository Clone <clone@altlinux.org> 1.0.0-alt1
- Initial build