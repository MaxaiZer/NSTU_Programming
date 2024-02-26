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

    public async Task<IEnumerable<Movie>> Get(int? limit, int? offset, float? minRating)
    {
        IQueryable<Movie> query = _context.Movies;

        if (minRating != null)
        {
            query = query.Where((m) => (m.ScoresSum * 1.0f / m.ScoresCount) >= minRating);
        }

        if (offset != null)
        {
            if (offset < 0) throw new InvalidArgumentException("Offset must be greater or equal than 0");
            query = query.Skip(offset.Value);
        }

        if (limit != null)
        {
            if (limit <= 0) throw new InvalidArgumentException("Limit must be greater than 0");
            query = query.Take(limit.Value);
        }

        return await query.ToListAsync();
    }

    public async Task<Movie?> GetById(int id)
    {
        return await _context.Movies.FindAsync(id);
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