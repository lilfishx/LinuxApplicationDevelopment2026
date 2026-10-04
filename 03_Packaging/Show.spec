Name:           Show
Version:        1.0.0
Release:        1
Group:          Other
License:        MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging
Source:         %name-%version.tar.gz
Summary:        Show package

BuildRequires:  ncurses

%description
Show package with minimal spec.

%prep
%setup -c

%build
%make_build

%install
install -D %name %buildroot%_bindir/%name

%files
%_bindir/*
