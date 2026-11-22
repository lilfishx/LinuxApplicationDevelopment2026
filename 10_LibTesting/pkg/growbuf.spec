Name:           growbuf
Version:        1.0.0
Release:        alt1
Summary:        Growable Memory Buffers for C99
Group:          Other
License:        MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/10_LibTesting
Source:         %name-%version.tar.gz

Packager: Repository Clone <clone@altlinux.org>

BuildRequires:  libcheck-devel autoconf automake autoconf-archive

%description
Growable Memory Buffers for C99

%package -n libgrowbuf
Summary:        Growable Memory Buffers for C99
Group:          Other

%description -n libgrowbuf
Growable Memory Buffers for C99

%package -n libgrowbuf-devel
Summary:        Growable Memory Buffers for C99 build environment
Group:          Other

%description -n libgrowbuf-devel
Growable Memory Buffers for C99 build environment

%prep
%setup -q

%build
%configure --disable-static
%make_build

%install
mkdir -p %buildroot

make install DESTDIR=%buildroot

%files -n libgrowbuf
%_libdir/lib*.so.*

%files -n libgrowbuf-devel
%_libdir/lib*.so
%_includedir/%name.h

%changelog
* Sun Nov 22 2026 Repository Clone <clone@altlinux.org> 1.0.0-alt1
- Initial build