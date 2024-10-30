def check_command(command)
  system("which #{command} > /dev/null 2>&1")
end

def generate_random_string(length)
  (0...length).map { ('A'..'Z').to_a.sample }.join
end

def calculate_difficulty(difficulty)
  (256 ** (4 - Math.log(difficulty.to_f) / Math.log(256))).to_i
end

def argon2_hash(password, salt, time_cost, memory_cost)
  # Placeholder for actual argon2 hashing
  # Use an external library or a system call to perform the hashing
  "00000000" # Simulated output
end

def main
  required_utils = ['argon2', 'xxd', 'bc']
  required_utils.each do |util|
    unless check_command(util)
      puts "#{util} is not installed. Please install it and try again."
      return
    end
  end

  challenge = ARGV[0] || (print "Enter Challenge Code: "; gets.strip)

  unless challenge =~ /^([0-9]+):([0-9]+):([A-Za-z0-9]+):([0-9]+)$/
    puts "Invalid challenge format. Expected format: memory_cost:time_cost:salt:difficulty"
    return
  end

  memory_cost, time_cost, salt, difficulty = challenge.split(':').map(&:strip)

  # Debugging output
  puts "Memory Cost: #{memory_cost}"
  puts "Time Cost: #{time_cost}"
  puts "Salt: #{salt}"
  puts "Difficulty: #{difficulty}"

  pw_prefix = "UNBLOCK-#{generate_random_string(8)}-"
  difficulty_raw = calculate_difficulty(difficulty)

  puts "Estimated iterations: #{difficulty}"
  puts "Time Cost: #{time_cost}\n"

  n = 1
  start_time = Time.now

  loop do
    pw = "#{pw_prefix}#{n}"
    hash = argon2_hash(pw, salt, time_cost, memory_cost)
    hash_bytes = hash[0..7]

    if hash_bytes.to_i(16) < difficulty_raw
      puts "\nSOLUTION FOUND"
      puts "Your unblock code is: #{pw}"
      puts "This is the code you enter into the site to pass the challenge.\n"
      return
    end

    elapsed_time = (Time.now - start_time).to_i
    print "\rElapsed Time: #{elapsed_time} seconds."
    n += 1
  end
end

main
