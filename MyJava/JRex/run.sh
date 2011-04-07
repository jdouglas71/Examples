export JAVA_HOME=$JAVA_HOME
export JREX_GRE_PATH=$HOME/jrex_gre
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
$JAVA_HOME/bin/java -cp ./JRex.jar -Djrex.dom.enable=true -Djrex.gre.path=$JREX_GRE_PATH -DJREX_DEBUG=true test.JRexExample
