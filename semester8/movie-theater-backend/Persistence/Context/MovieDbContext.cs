using Microsoft.EntityFrameworkCore;
using Domain.Entities;

namespace Persistence.Context;

public class MovieDbContext : DbContext
{
    public DbSet<Movie> Movies { get; set; }

    public DbSet<Country> Countries { get; set; }

    public DbSet<Genre> Genres { get; set; }

    public MovieDbContext(DbContextOptions<MovieDbContext> options) : base(options)
    {

    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);

        modelBuilder.Entity<Movie>().ToTable("movies");
        modelBuilder.Entity<Country>().ToTable("countries");
        modelBuilder.Entity<Genre>().ToTable("genres");

        modelBuilder.Entity<Country>().HasData(
        new
        {
            Id = 1,
            Name = "Россия"
        },
        new
        {
            Id = 2,
            Name = "США"
        }
        );

        modelBuilder.Entity<Genre>().HasData(
        new
        {
            Id = 1,
            Name = "Мелодрама"
        },
        new
        {
            Id = 2,
            Name = "Ужасы"
        },
        new
        {
            Id = 3,
            Name = "Драма"
        }
        );
    }

}
