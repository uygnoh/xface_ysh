#!/bin/bash
set -e



if [ ! -d ~/.config/rox.sourceforge.net/MIME-types ]; then
    mkdir -p ~/.config/rox.sourceforge.net/MIME-types
fi
cat > ~/.config/rox.sourceforge.net/MIME-types/application_x-shellscript <<\EOF
#!/bin/bash
exec "$@"
EOF


if [ ! -d ~/.config/rox.sourceforge.net/MIME-types ]; then
    mkdir -p ~/.config/rox.sourceforge.net/MIME-types
fi
cat > ~/.config/rox.sourceforge.net/MIME-types/text <<\EOF
#!/bin/bash
exec gedit "$@"
EOF


if [ ! -d ~/.config/rox.sourceforge.net/MIME-types ]; then
    mkdir -p ~/.config/rox.sourceforge.net/MIME-types
fi
cat > ~/.config/rox.sourceforge.net/MIME-types/smplayer <<\EOF
#!/bin/bash
exec smplayer "$@"
EOF


cd ~/.config/rox.sourceforge.net/MIME-types
chmod 755 *


