require 'bcrypt'
require_relative 'user'

class Authenticator

    @user_list = Hash.new

    def self.create_user_password (password)
        return BCrypt::Password.create(password)
    end

    def self.verify_user_password(password)
        return BCrypt::Password.new(password)
    end

    def self.create_user(username, password, email, name)
        @user_list[username] = User.new(username, create_user_password(password), email, name)
    end

    def self.authenticate_user(username, password)
            if !@user_list[username].nil?
                user = @user_list[username]
                return verify_user_password(user.password) == password 
            end
        puts "Username was not found"
    end
end