SET JAVA_HOME=%JAVA_HOME%
SET JREX_GRE_PATH=c:/jrex_gre
%JAVA_HOME%/bin/java -cp ./JRex.jar -Djrex.dom.enable=true -Djrex.gre.path=%JREX_GRE_PATH% -DJREX_DEBUG=true test.JRexExample