# Check if required utilities are installed
def check_utility(utility)
  system("command -v #{utility} > /dev/null 2>&1")
  end

  required_utils = ['argon2', 'xxd', 'bc']

  required_utils.each do |utils|
    unless check_utility(utils)
        puts "#{utils} is not installed. Please install it and try again."
            exit(1)
              end
              end

              # Read the challenge code from argument or prompt user
              challenge = ARGV[0] || (print "Enter Challenge Code: "; gets.chomp)

              # Validate the challenge format
              unless challenge.match?(/^(\d+):(\d+):([A-Za-z0-9]+):(\d+)$/)
                puts "Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty"
                  exit(2)
                  end

                  # Parse challenge code
                  memory_cost, time_cost, salt, difficulty = challenge.split(':').map(&:strip)

                  # Debugging output
                  puts "Memory Cost: #{memory_cost}"
                  puts "Time Cost: #{time_cost}"
                  puts "Salt: #{salt}"
                  puts "Difficulty: #{difficulty}"

                  # Generate prefix for the password
                  pw_prefix = "UNBLOCK-#{(0...8).map { ('A'..'Z').to_a.sample }.join}-"
                  difficulty_raw = (Math::E**(Math.log(256) * (4 - Math.log(difficulty.to_i) / Math.log(256)))).to_i

                  puts "Estimated iterations: #{difficulty}"
                  puts "Time Cost: #{time_cost}\n"

                  n = 1
                  start_time = Time.now

                  # Function to display elapsed time
                  def elapsed_time(start_time)
                    elapsed = Time.now - start_time
                      print "\rElapsed Time: #{elapsed.to_i} seconds."
                      end

                      # Main loop to find the solution
                      loop do
                        pw = "#{pw_prefix}#{n}"
                          hash_result = `echo -n "#{pw}" | argon2 #{salt} -t #{time_cost} -k #{memory_cost} -p 1 -id -v 13 -r`
                            
                              hash_bytes = hash_result.split('$')[3][0..7]  # Extract the first 8 characters of the hash
                                
                                  if hash_bytes.to_i(16) < difficulty_raw
                                      puts "\nSOLUTION FOUND"
                                          puts "Your unblock code is: #{pw}"
                                              puts "This is the code you enter into the site to pass the challenge.\n"
                                                  break
                                                    else
                                                        elapsed_time(start_time)
                                                            n += 1
                                                              end
                                                              end