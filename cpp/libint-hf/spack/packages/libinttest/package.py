from spack import *

class Libinttest(CMakePackage):
    version("dev")
    depends_on("cmake")
    depends_on("libint@2.7.2")
    depends_on("eigen")