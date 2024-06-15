#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <cstdlib>

enum class TokenType {exit, int_lit, semi, open_paren, close_paren };

struct Token
{
    TokenType type;
    std::optional<std::string> value{};
};

class [[maybe_unused]] Tokenizer {
public:
    inline explicit Tokenizer(std::string src)
    :m_src(std::move(src)){

    }

    inline std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit") {
                    tokens.push_back({TokenType::exit});
                    buf.clear();
                    continue;
                } else {
                    std::cerr << "You messed up!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while(peek().has_value() && std::isdigit(peek().value())){
                    buf.push_back(consume());
                }
                tokens.push_back({TokenType::int_lit, buf});
                buf.clear();
            }
            else if (peek().value() == '('){
                consume();
                tokens.push_back({.type = TokenType::open_paren});
            }
            else if (peek().value() == ')'){
                consume();
                tokens.push_back({.type = TokenType::close_paren});
            }
            else if (peek().value() == ';'){
                consume();
                tokens.push_back({TokenType::semi});
                continue;
            }
            else if (std::isspace(peek().value())){
                consume();
                continue;
            }else{
                std::cerr << "You messed up!" <<std::endl;
                exit(EXIT_FAILURE);
            }
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] inline std::optional<char> peek() const {
        if (m_index + 0 >= m_src.length()) {
            return {};
        } else {
            return m_src.at(m_index + 0);
        }
    }

    inline char consume() {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index=0;
};
