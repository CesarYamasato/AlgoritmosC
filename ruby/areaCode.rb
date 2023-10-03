dial_dict = {
    "São Paulo"=> 1,
    "Rio De Janeiro"=> 2,
    "Espírito Santo"=> 3,
    "Salvador"=>4,
    "Maceió"=>5,
    "Petrolina"=>6,
    "Curitiba"=> 7,
    "Sorocaba"=> 8,
    "Alumínio"=>9
}

def get_city_names(hash)
    hash.each{ |k, v| puts k}
end

def intro(hash)
    while true
    puts "Do you want to get area code? (Y/y)"
        if gets.chomp.downcase == "y"
            get_city_names(hash)
            puts "Wich city do you want to get the code to?"
            puts hash[gets.chomp]

        else
            if gets.chomp.downcase == "n"
                return
            end
        end
    end

end

puts "Do you want to get area code? (Y/y)"

while gets.chomp.downcase == "y"
    get_city_names(dial_dict)
    puts "Wich city do you want to get the code to?"
    lookup = gets.chomp
    if !dial_dict[lookup].nil?
        puts dial_dict[lookup]
    else puts "City not available"
    end
    puts "Do you want to get area code? (Y/y)"
end
