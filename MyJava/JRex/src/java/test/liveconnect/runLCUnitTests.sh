export JAVA_HOME=$JAVA_HOME
export MOZ_HOME=$MOZ_HOME
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
$JAVA_HOME/bin/java -cp ../../../../classes:$JAVA_HOME/jre/lib/plugin.jar:$JAVA_HOME/jre/lib/deploy.jar -Djrex.dom.enable=true -Djrex.gre.path=$MOZ_HOME/bin -DJREX_DEBUG=true test.liveconnect.JRexLiveConnectSessionUnitTest lcSession_unitTest.html
