SET JAVA_HOME=%JAVA_HOME%
SET MOZ_HOME=%MOZ_HOME%
SET PATH=%MOZ_HOME%\bin;%JAVA_HOME%\jre\bin;%PATH%
%JAVA_HOME%/bin/java -Xmx50M -Xcheck:jni -cp ../../../../classes;%JAVA_HOME%\jre\lib\plugin.jar;%JAVA_HOME%\jre\lib\deploy.jar -Djrex.dom.enable=true -Djrex.gre.path=%MOZ_HOME%/bin -DJREX_DEBUG=false test.liveconnect.JRexLiveConnectSessionUnitTest lcSession_unitTest.html %1  
