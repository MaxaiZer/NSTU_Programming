using Domain.Repositories;
using Domain.Entities;
using Persistence.Context;
using Microsoft.EntityFrameworkCore;

namespace Persistence.Repositories;

public class MovieRepository : IMovieRepository
{
    protected readonly MovieDbContext _context;
    public MovieRepository(MovieDbContext dbContext)
    {
       _context = dbContext;
    }

    public async Task<IEnumerable<Movie>> Get(float? minRating)
    {
        return await _context.Movies.Where((m) => (m.ScoresSum * 1.0f / m.ScoresCount) >= minRating).ToListAsync();
    }

    public async Task Add(Movie movie)
    {
        await _context.Movies.AddAsync(movie);
    }

    public void Save()
    {
        _context.SaveChanges();
    }
}