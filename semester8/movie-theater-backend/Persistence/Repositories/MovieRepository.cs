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

    public async Task<IEnumerable<Movie>> Get(MovieSearchParams parameters)
    {
        IQueryable<Movie> query = _context.Movies;

        if (parameters.MinRating != null)
        {
            query = query.Where((m) => (m.ScoresSum * 1.0f / m.ScoresCount) >= parameters.MinRating);
        }

        if (parameters.IsForeign != null)
        {
            query = query.Where((m) => m.Country.Name != "Россия");
        }

        if (parameters.Offset != null)
        {
            if (parameters.Offset < 0) throw new ArgumentOutOfRangeException("Offset must be greater or equal than 0");
            query = query.Skip(parameters.Offset.Value);
        }

        if (parameters.Limit != null)
        {
            if (parameters.Limit <= 0) throw new ArgumentOutOfRangeException("Limit must be greater than 0");
            query = query.Take(parameters.Limit.Value);
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