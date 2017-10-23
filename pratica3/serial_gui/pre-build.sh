if type -p qmake-qt5 > /dev/null;
    then
        qmake-qt5 $*
        echo ">> Pre-build complete with Qt 5!!"
    else
        if type -p qmake-qt4 > /dev/null;
            then
                qmake-qt4 $*
                echo ">> Pre-build complete with Qt 4!!"
            else
                if type -p qmake > /dev/null;
                    then
                        qmake $*
                        echo ">> Pre-build complete!!"
                    else
                        echo ">> Could not generate Makefile!!"
                fi
        fi
fi
