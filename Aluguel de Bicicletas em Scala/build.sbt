name := "BikeRent"

// Project version
version := "8.0.102-R11"

// Version of Scala used by the project
scalaVersion := "2.12.2"

// Add dependency on ScalaFX library
resourceDirectory in Compile := (scalaSource in Compile).value
libraryDependencies += "org.scalafx" %% "scalafx" % "8.0.102-R11"
libraryDependencies += "org.xerial" % "sqlite-jdbc" % "3.8.11.2"
libraryDependencies += "org.scalafx" %% "scalafxml-core-sfx8" % "0.3"

addCompilerPlugin("org.scalamacros" % "paradise" % "2.1.0" cross CrossVersion.full)

scalacOptions ++= Seq("-unchecked", "-deprecation", "-Xcheckinit", "-encoding", "utf8", "-feature")

// Fork a new JVM for 'run' and 'test:run', to avoid JavaFX double initialization problems
fork := true