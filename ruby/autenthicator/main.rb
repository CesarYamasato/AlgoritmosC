require_relative 'lib/authenticator'

Authenticator.create_user("cesar", "senha1", "cesar-byb1@hotmail.com", "César")
Authenticator.create_user("cesar2", "senha2", "cesar-byb1@hotmail.com", "César")
Authenticator.create_user("cesar3", "senha3", "cesar-byb1@hotmail.com", "César")

puts Authenticator.authenticate_user("cesar", "senha2")