class User 
    attr_reader :username, :name, :password

    @username
    @password
    @email
    @name

    def initialize(username, password, email, name)
        @username = username
        @email = email
        @name = name
        @password = password
    end

    def to_s
        @username
    end
end