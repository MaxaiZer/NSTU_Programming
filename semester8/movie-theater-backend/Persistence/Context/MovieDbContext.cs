using Microsoft.EntityFrameworkCore;
using Domain.Entities;

namespace Persistence.Context;

public class MovieDbContext : DbContext
{
    public DbSet<Movie> Movies { get; set; }

    public MovieDbContext(DbContextOptions<MovieDbContext> options) : base(options)
    {

    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);

        modelBuilder.Entity<Movie>().ToTable("movies");
    }

}
