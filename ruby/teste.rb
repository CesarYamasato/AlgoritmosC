address = [1,2,3,4,5,6,7,8,9]
puts 'hello'
p address[2]
p address.reverse!
5.times{p address}
def tomaNoCu
    input = gets.chomp
    if input.eql?("vai tomar no cu")    
        puts "vai você"
    else
        puts "então de boa"
    end
end

while true
    tomaNoCu
end

