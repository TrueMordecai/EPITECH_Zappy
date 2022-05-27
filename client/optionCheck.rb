# Check options passed in command line
# @param ARGV [Array] must be command line option
# return [Hash] under the form {"-[pnh]", [$port, $name, $host]}
def optionsCheck(argv)
    options = {}
    options["host"] = "localhost"
    for i in 0..argv.size - 1 do
        for opt in [["-p", "port"], ["-n", "name"], ["-h", "host"]]
            if (argv[i] == opt[0] and i + 1 <= argv.size - 1 and !argv[i + 1].include?('-'))
                options[opt[1]] = argv[i + 1]
            end
        end
    end
    if (options["port"].nil? or options["name"].nil?)
        STDERR.print("ERROR : No port or name specified\n")
        exit (84)
    end
    return (options)
end