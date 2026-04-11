//
// Created by tysser on 11.04.26.
//

#include <iostream>


namespace original
{
    class Vect;
    void implementation();
}

namespace fixed
{
    class Vect;
    void implementation();
}

int main() {
    fixed::implementation();
    //original::implementation();

    return 0;
}

namespace original
{
    class Vect {
    public:
        Vect(char); // char від -128 до 127

        ~Vect()

        {
            delete [] p_;
        }

        int& operator [] (int i)
        {
            return p_[i];
        }

        void Print();

    private:
        int* p_;
        char size_;
    };

    Vect::Vect(char n) : size_(n)
    {
        p_ = new int[size_];
        if (!p_) {
            std::cerr << "Error of Vect constructor" << std::endl;
            return ;
        }
        for(int i=0;i<size_;++i) p_[i]=int();
    }

    void Vect::Print()
    {
        for (int i = 0; i < size_; ++i)
            std::cout<< p_[i]<< " ";
        std::cout<< std::endl;
    }

    void implementation()
    {
        Vect a(3);
        a[0]=0;
        a[1]=1;
        a[2]= 2;
        a.Print();
        Vect a1(200);
        a1[10] = 5;
        a1.Print();
    }
}

namespace fixed
{
    class Vect
    {
    public:
        // =======================================================================================
        // explicit - забороняє компілятору робити неявне перетворення типів (implicit conversion)
        explicit Vect(const char n) : p_(nullptr), size_(n)
        {
            try
            {
                const auto real_size = static_cast<unsigned char>(size_); // 0...255

                if (real_size == 0) throw std::invalid_argument("Недійсний розмір");

                p_ = new int[real_size];

                for (unsigned int i = 0; i < real_size; ++i) p_[i] = 0;
            }
            catch (const std::exception& ex)
            {
                std::cerr << "Помилка конструктора: " << ex.what() << std::endl;
                throw;
            }
        }

        // =======================================================================================
        ~Vect()
        {
            try
            {
                delete[] p_;
                p_ = nullptr;
            }

            catch (...)
            {
                std::cerr << "Помилка деструктора" << std::endl;
            }
        }

        // =======================================================================================
        int& operator[](const int i)
        {
            if (p_ == nullptr) throw std::logic_error("Пам'ять не виділена");

            const auto real_size = static_cast<unsigned char>(size_);

            if (i < 0 || i >= real_size) throw std::out_of_range("Індекс поза діапазоном");

            return p_[i];
        }

        // =======================================================================================
        void Print() const
        {
            if (p_ == nullptr) throw std::logic_error("Пам'ять не виділена");

            const auto real_size = static_cast<unsigned char>(size_);

            for (unsigned int i = 0; i < real_size; ++i) std::cout << p_[i] << " ";

            std::cout << std::endl;
        }

    private:
        int* p_;
        char size_;
    };

    void implementation()
    {
        try
        {
            Vect a(3);
            a[0] = 0;
            a[1] = 1;
            a[2] = 2;
            a.Print();

            Vect a1(200);
            a1[10] = 5;
            a1.Print();
        }

        catch (const std::exception& ex)
        {
            std::cerr << "Помилка: " << ex.what() << std::endl;
        }

        catch (...)
        {
            std::cerr << "Невідома помилка" << std::endl;
        }
    }
}